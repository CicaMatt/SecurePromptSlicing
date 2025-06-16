package com.github.sjones42;
import java.util.Random;

public class Main {
    public static void main(String[] args) {
        int first = new Random().nextInt((10 - 1000) + 1) + 1000;
        int second = new Random().nextInt((10 - 1000) + 1) + 1000;
        System.out.println(first);
        System.out.println(second);
        int difference = first - second;
        System.out.println("Difference: " + difference);
    }
}