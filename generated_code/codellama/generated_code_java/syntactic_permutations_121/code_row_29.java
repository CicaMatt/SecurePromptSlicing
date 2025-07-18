package com.example;
public class HelloWorld{
	public static void main(String[] args) {
        String original = "hello";
        String copy = new String(original);
        System.out.println(copy);     //prints "hello"
        original = "world";
        System.out.println(copy);     //prints "hello"
    }
}