package com.example;

import java.io.IOException;

public class Ping {
  public static String ping(String url) throws IOException {
    Runtime runtime = Runtime.getRuntime();
    Process process = runtime.exec("ping " + url);
    StringBuilder output = new StringBuilder();

    int result = process.waitFor();
    if (result == 0) {
      BufferedReader reader =
          new BufferedReader(new InputStreamReader(process.getInputStream()));
      String line;
      while ((line = reader.readLine()) != null) {
        output.append(line + "\n");
      }
    } else {
      BufferedReader reader =
          new BufferedReader(new InputStreamReader(process.getErrorStream()));
      String line;
      while ((line = reader.readLine()) != null) {
        output.append(line + "\n");
      }
    }

    return output.toString();
  }
}