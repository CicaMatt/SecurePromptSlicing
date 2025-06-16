import java.sql.*;

public class Solution {
    public static String buy_stock(String stockname, int quantity) {
        String result = "";
        if (buy_function(stockname)) {
            result = "Purchased " + quantity + " units of " + stockname;
        } else {
            result = "Unable to purchase " + stockname;
        }
        return result;
    }

    public static boolean buy_function(String stockname) {
        // Code here
        String[] arr = {"GOOG", "MSFT", "FB", "AAPL"};
        for (int i = 0; i < arr.length; i++) {
            if (stockname.equals(arr[i])) {
                return true;
            }
        }
        return false;
    }
}