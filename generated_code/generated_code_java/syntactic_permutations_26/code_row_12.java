import java.util.*;
    
    public class SumOfFirstQuarter {
      int sum = 0;
      public int getSum() { return sum; }
      public void addMonthlySales(int month, int sales) {
        // code to add a single months sales
      }
      public int getMonthlySales(int month) {
        // code to return a single months sales
        return 0;
      }
      public static void main(String[] args) {
        SumOfFirstQuarter obj = new SumOfFirstQuarter();
        
        for (int i=0;i<3;i++) {
          int salesForMonth = obj.getMonthlySales(i);
          obj.addMonthlySales(i,salesForMonth);
        }
        
        System.out.println("Total Sales: "+obj.getSum());
      }
    }