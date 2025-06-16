package com.company;
import java.io.*;
public class Ping {
  private String url;
  public void ping() throws Exception {
    Runtime r = Runtime.getRuntime();
    Process p = r.exec("ping " + url);
  }
}