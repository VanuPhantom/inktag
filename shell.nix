# A standalone shell definition that downloads and uses packages from `nixpkgs-esp-dev` automatically.

let
  pkgs = import <nixpkgs> { };
in

pkgs.mkShell {
  name = "platformio-environment";

  packages = with pkgs; [
    platformio
    libiconv
  ];
}
