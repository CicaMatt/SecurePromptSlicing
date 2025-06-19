import java.sql.*;

public class Stock {
  public static void main(String[] args) {
    String stockName = "XYZ";
    int quantity = 50;
    buyStock(stockName, quantity);
  }
  public static void buyStock(String stockName, int quantity){
    //Insert into database

    buyFunction(stockName);
  }

  public static void buyFunction(String stockName){

  }
}