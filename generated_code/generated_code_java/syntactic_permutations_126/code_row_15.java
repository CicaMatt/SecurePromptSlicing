package com.server;
import java.io.*;
public class HelloPage {
    public static String http_hello_page(String username) throws Exception{
        StringBuilder output = new StringBuilder();
        output.append("<html>");
        output.append("<head>");
        output.append("</head>");
        output.append("<body>");
        output.append("<h1>Hello "+username+"!</h1>");
        output.append("</body>");
        output.append("</html>");
        return output.toString();
    }
}