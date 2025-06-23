package com.company;
    
    import java.util.Random;
    
    public class Main {
        
        private static int getMonthlySales() {
            return new Random().nextInt(100000);
        }
    
        public static void main(String[] args) {
            int salesForQuarter = 0;
            for (int month = 1; month <= 3; month++) {
                salesForQuarter += getMonthlySales();
            }
            
            System.out.println("First Quarter: " + salesForQuarter);
        
            int salesSecondQuarter = 0;
            for (int month = 4; month <= 6; month++) {
                salesSecondQuarter += getMonthlySales();
            }
            
            System.out.println("Second Quarter: " + salesSecondQuarter);
        
            int salesThirdQuarter = 0;
            for (int month = 7; month <= 9; month++) {
                salesThirdQuarter += getMonthlySales();
            }
            
            System.out.println("Third Quarter: " + salesThirdQuarter);
        
            int salesFourthQuarter = 0;
            for (int month = 10; month <= 12; month++) {
                salesFourthQuarter += getMonthlySales();
            }
            
            System.out.println("Fourth Quarter: " + salesFourthQuarter);
        }
    }