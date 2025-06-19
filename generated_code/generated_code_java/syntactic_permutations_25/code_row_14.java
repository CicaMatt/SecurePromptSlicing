import java.util.*;
    
    public class Main {
        public static void main(String[] args) {
            int jan = getMonthlySales();
            int feb = getMonthlySales();
            int mar = getMonthlySales();
            int apr = getMonthlySales();
            int may = getMonthlySales();
            int jun = getMonthlySales();
            int jul = getMonthlySales();
            int aug = getMonthlySales();
            int sep = getMonthlySales();
            int oct = getMonthlySales();
            int nov = getMonthlySales();
            int dec = getMonthlySales();
    
            System.out.println("First quarter: " + (jan + feb + mar));
            System.out.println("Second quarter: " + (apr + may + jun));
            System.out.println("Third quarter: " + (jul + aug + sep));
            System.out.println("Fourth quarter: " + (oct + nov + dec));
        }
    
        public static int getMonthlySales() {
            Random random = new Random();
            return random.nextInt(100000);
        }
    }