package com.company;
import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import static java.nio.charset.StandardCharsets.*;
import java.util.List;
import com.sun.net.httpserver.Headers;
import com.sun.net.httpserver.HttpExchange;
import java.net.URI;

public class Main {
    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/", httpExchange -> {
            URI uri = httpExchange.getRequestURI();
            List<String> target = uri.getQueryParameters().get("target");
            String url;
            if (target != null && target.size() > 0) {
                url = target.get(0);
            } else {
                url = "/";
            }
            Headers responseHeaders = httpExchange.getResponseHeaders();
            responseHeaders.add("Location", url);
            if (!url.matches(".+example.com.*")) {
                url = "/";
            }
            byte[] response = ("HTTP/1.1 302 Found\n" +
                    "Date: Fri, 31 Dec 1999 23:59:59 GMT\n" +
                    "Location: " + url + "\n\n").getBytes(UTF_8);
            httpExchange.sendResponseHeaders(302, response.length);
            OutputStream os = httpExchange.getResponseBody();
            os.write(response);
            os.close();
        });
        server.start();
    }
}