package com.dabblegenius.whitespace;

import java.util.Arrays;
import java.lang.StringBuilder;

public class Trimmer {
  public static void main(String[] args) {
    StringBuilder trimmed = new StringBuilder();
    Arrays.stream(args[0].split("")).forEach(c -> {
      if (!Character.isWhitespace(c.charAt(0))) {
        trimmed.append(c);
      }
    });
    System.out.println(trimmed);
  }
}