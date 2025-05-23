{ pkgs ? import <nixpkgs> { } }:

pkgs.mkShell rec {

  buildInputs = [
    pkgs.cmake
    pkgs.arduino-language-server
    pkgs.arduino-cli
    pkgs.clang-tools
    pkgs.python312Packages.speechrecognition
    pkgs.python312Packages.pyaudio
    pkgs.python312Packages.pyserial
    pkgs.python312Packages.python-lsp-server
    pkgs.python312Packages.sounddevice

  ];

  shellHook = ''
    export LD_LIBRARY_PATH="${pkgs.lib.makeLibraryPath buildInputs}:$LD_LIBRARY_PATH"
    export LD_LIBRARY_PATH="${pkgs.stdenv.cc.cc.lib.outPath}/lib:$LD_LIBRARY_PATH"
  '';
}
