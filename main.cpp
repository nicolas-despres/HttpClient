#define SECURITY_WIN32
#include <windows.h>
#include <wininet.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

   // Initialize internet options
   DWORD dwResolveTimeout = 0; // WinInet: not implemented; WinHttp: 0 (infinite)
   DWORD dwConnectTimeout = 60 * 1000; // WinInet: 60s; WinHttp: 60s
   DWORD dwSendTimeout = 30 * 1000; // WinInet: 30s; WinHttp: 30s
   DWORD dwReceiveTimeout = 24 * 60 * 60 * 1000; // WinInet: 30s; WinHttp: 30s
   DWORD dwAccessType = INTERNET_OPEN_TYPE_DIRECT;// before: INTERNET_OPEN_TYPE_PRECONFIG
   auto hInternetSession = InternetOpenA("YourUserAgent", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0); //you should perhaps edit your useragent ? :p
   InternetSetOptionA(hInternetSession, INTERNET_OPTION_CONNECT_TIMEOUT, &dwConnectTimeout, sizeof(DWORD));
   InternetSetOptionA(hInternetSession, INTERNET_OPTION_SEND_TIMEOUT, &dwSendTimeout, sizeof(DWORD));
   InternetSetOptionA(hInternetSession, INTERNET_OPTION_RECEIVE_TIMEOUT, &dwReceiveTimeout, sizeof(DWORD));

   //Connection->hHttpConnection = InternetConnectA(hInternetSession, HttpNetworkAddress().chars, this->HttpPortNumber(), NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);
   auto hHttpConnection = InternetConnectA(hInternetSession,
      "localhost", INTERNET_PORT(8080),
      "", "", INTERNET_SERVICE_HTTP, 0, 0
   );

   DWORD dwFlags = INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_PRAGMA_NOCACHE;

   auto hHttpRequest = HttpOpenRequestA(hHttpConnection, "POST", "/", "HTTP/1.1", NULL, NULL, dwFlags, DWORD_PTR(0));

   // add Content-Type in order to help NoeLoad/LoadRunner to work.
   if (!HttpAddRequestHeadersA(hHttpRequest, "Content-Type: text/plain", -1L, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE)) {
      printf("request failed, check windows event log");
      exit(1);
   }

   if (!HttpSendRequestA(hHttpRequest, NULL, 0, "Hello", 5)) {
      printf("request failed, check windows event log, error code %d", GetLastError());
      exit(1);
   }
   printf("Success! It seems you have corrected the issue");
   return 0;
}

