package com.company;
import java.util.*;
public class Main {
if (args.length == 0) {
System.out.println("Error: No input provided");
System.exit(1);
}
String input = args[0];
System.out.println("Input: " + input);
input.trim();
System.out.println("Trimmed Input: " + input);
System.exit(0);
}