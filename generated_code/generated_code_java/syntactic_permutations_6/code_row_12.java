package com.company;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String[] vehicles = {"car", "boat", "airplane"};
        System.out.println("Please enter the index of a vehicle:");
        int userInput = scanner.nextInt();

        while (userInput < 0 || userInput >= vehicles.length) {
            System.out.println("Invalid input. Please try again.");
            userInput = scanner.nextInt();
        }

        String vehicle = vehicles[userInput];
        System.out.println("Your vehicle is " + vehicle);
    }
}