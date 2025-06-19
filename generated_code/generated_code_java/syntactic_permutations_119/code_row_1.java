package com.example.java_test;

import java.util.Random;

public class Test {
    public static void main(String[] args) {
        Random rand = new Random();
        float a = rand.nextFloat() * 100;
        float b = rand.nextFloat() * 100;
        float c = rand.nextFloat() * 100;

        String string = String.format("%f", a);
        String string2 = String.format("%f", b);
        String string3 = String.format("%f", c);
    }
}