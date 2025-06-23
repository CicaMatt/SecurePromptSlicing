package com.company;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class Main extends HttpServlet {

    public static void main(String[] args) throws IOException, ServletException {
        Scanner in = new Scanner(System.in);
        int option = 0;
        while (option != -1) {
            System.out.println("Welcome to the Store!");
            System.out.println("What would you like to do?");
            System.out.println("1. Add a new product");
            System.out.println("2. List all products");
            System.out.println("3. Remove a product");
            System.out.println("4. Calculate cost of an order");
            System.out.println("-1. Exit");

            option = in.nextInt();

            switch (option) {
                case 1:
                    System.out.print("Product code: ");
                    String productCode = in.nextLine();
                    System.out.print("Quantity: ");
                    int quantity = in.nextInt();
                    System.out.println("Added to cart");
                    break;
                case 2:
                    System.out.println("Product code\tQuantity");
                    for (HashMap<String, Integer> entry : cart) {
                        System.out.println(entry.getKey() + "\t" + entry.getValue());
                    }
                    break;
                case 3:
                    System.out.print("Product code to remove: ");
                    String productCodeToRemove = in.nextLine();
                    if (cart.containsKey(productCodeToRemove)) {
                        cart.remove(productCodeToRemove);
                        System.out.println("Removed from cart");
                    } else {
                        System.out.println("Product not found in cart");
                    }
                    break;
                case 4:
                    int total = 0;
                    for (HashMap<String, Integer> entry : cart) {
                        String productCode = entry.getKey();
                        int quantity = entry.getValue();
                        if (products.containsKey(productCode)) {
                            int price = products.get(productCode);
                            total += quantity * price;
                        } else {
                            System.out.println("Product not found");
                        }
                    }
                    System.out.println("Total: " + total);
                    break;
                case -1:
                    System.out.println("Thank you for shopping!");
                    System.exit(0);
            }
        }
    }
}