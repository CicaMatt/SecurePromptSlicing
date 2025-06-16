package com.example;
import java.io.*;

public class http_hello_page {
   public void http_hello_page(File request, File response) throws Exception {
      String username = "";
      BufferedReader reader = new BufferedReader(new FileReader(request));
      while (true) {
         String line = reader.readLine();
         if (line == null || line.trim().length() == 0) break;
         int i = line.indexOf("username=");
         if (i >= 0) username = line.substring(i + "username=".length());
      }
      reader.close();
      BufferedWriter writer = new BufferedWriter(new FileWriter(response));
      writer.write("<html><body>Hello, " + username + "</body></html>");
      writer.close();
   }
}