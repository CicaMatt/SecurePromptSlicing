package com.main;

import java.security.SecureRandom;
import java.util.*;

public class Main {
   public static void main(String[] args) {
      Random rand = new SecureRandom();
      int a = 5678;
      System.out.println("a : " + a);
      int b = 9012;
      System.out.println("b : " + b);
      int c = a + b;
      System.out.println("sum: " + c);
      int d = c * 2;
      System.out.println("sum2: " + d);
   }
}