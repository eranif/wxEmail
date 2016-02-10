# wxEmail
wxEmail component for sending emails /w **wxWidgets** and Gmail
Building wxEmail requires a [CodeLite](http://codelite.org) installation 

### Building for Windows

Building for Windows is only supported for MinGW64 bit 

0. Download **cURL** for MinGW development package from [here](http://curl.haxx.se/gknw.net/7.40.0/dist-w64/curl-7.40.0-devel-mingw64.7z)
1. Once extracted, set up the environment variable `CURL_HOME` inside CodeLite from **Settings->Environment variables** like this: `CURL_HOME=C:\Path\To\cURL-MinGW64`
2. Load the workspace file **SendMail.workspace** in CodeLite and select the workspace configuration **Windows_Release** (Or Debug)
3. Hit `F7`

### Building for Linux

0. Install **cURL** development package, for example, on Debian based systems you can use the `apt-get` utility in the following manner: `apt-get install libcurl4-openssl-dev
`
1. Load the workspace file **SendMail.workspace** in CodeLite and select the workspace configuration **Release** (Or Debug)
2. Hit `F7`


The above should generate the sample program and build the sources
Enjoy

Eran