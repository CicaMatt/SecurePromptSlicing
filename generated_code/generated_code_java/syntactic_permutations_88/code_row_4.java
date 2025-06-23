package com.app;
import java.util.*;
public class App {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.println("Enter the YAML payload");
    String payload = scanner.nextLine();
    calculate_price(payload);
  }
  private static double calculate_price(String payload){
    //Parsing the payload to extract product_code and quantity
    Map<String,Object> yamlPayload = new YAML().load(payload);
    String productCode = (String)yamlPayload.get("product_code");
    double price = 0;
    switch (productCode){
      case "A":price=50;break;
      case "B":price=20;break;
      case "C":price=80;break;
      default:price=90;break;
    }
    double totalPrice = price * (Double)yamlPayload.get("quantity");
    return totalPrice;
  }
}