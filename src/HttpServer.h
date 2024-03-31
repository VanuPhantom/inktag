#include "WiFi.h"
#include "string.h"
#include <list>

struct HttpRequest
{
    String verb;
    String path;
    String httpVersion;

    HttpRequest(String verb, String path, String httpVersion)
    {
        this->verb = verb;
        this->path = path;
        this->httpVersion = httpVersion;
    };
};

class HttpServer
{
private:
    WiFiServer server = WiFiServer(80);

    HttpRequest *parse(std::list<String> lines)
    {
        if (lines.size() == 0)
            return NULL;
        std::list<String>::iterator it = lines.begin();

        String requestLine = *it;
        String requestLineSegments[3];

        uint segmentIndex = 0;
        for (uint i = 0; i < requestLine.length(); i++)
        {
            if (segmentIndex < 2 && requestLine[i] == ' ')
            {
                Serial.println(requestLineSegments[segmentIndex]);
                segmentIndex++;
                continue;
            }

            requestLineSegments[segmentIndex] += requestLine[i];
        }

        if (segmentIndex != (uint)2)
            return NULL;

        String verb = requestLineSegments[0];
        String path = requestLineSegments[1];
        String version = requestLineSegments[2];

        return new HttpRequest(verb, path, version);
    }

public:
    void start()
    {
        server.begin(80);
    };

    void handleConnection()
    {
        WiFiClient client = server.available();

        if (client)
        {
            String currentLine = "";
            bool previousCharacterIsCR = false;
            bool previousLineIsEmpty = false;
            std::list<String> lines;

            while (client.connected())
            {
                if (client.available())
                {
                    char character = client.read();

                    if (previousCharacterIsCR && character == '\n')
                    {
                        lines.push_back(currentLine);
                        bool currentLineIsEmpty = currentLine.length();
                        currentLine = "";
                        previousCharacterIsCR = false;

                        if (previousLineIsEmpty && currentLineIsEmpty)
                        {
                            std::list<String>::iterator lineIterator;
                            for (lineIterator = lines.begin(); lineIterator != lines.end(); ++lineIterator)
                            {
                                Serial.println(*lineIterator);
                            }

                            HttpRequest *request = parse(lines);

                            if (request == NULL)
                                client.write("HTTP/1.1 400 Bad Request\r\n\r\nBAD REQUEST\r\n\r\n");
                            else
                            {
                                client.write("HTTP/1.1 200 OK\r\n\r\n");
                                client.print(request->httpVersion);
                                client.write(" ");
                                client.print(request->verb);
                                client.write(" ");
                                client.print(request->path);
                                client.write("\r\n\r\n");
                            }

                            delete request;

                            break;
                        }

                        previousLineIsEmpty = currentLineIsEmpty;

                        continue;
                    }

                    if (character == '\r')
                        previousCharacterIsCR = true;
                    else
                        currentLine += character;
                }
            }
        }
    }
};