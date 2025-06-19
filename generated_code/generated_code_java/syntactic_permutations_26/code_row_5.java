import java.util.*;
    public class Sales {
        int sum = 0;
        public void iterateOverQuarter() {
            for (int i=0; i<3;i++) {
                sum += getMonthlySales(i);
            }
        }
    
        public int getMonthlySales(int month) {
            return 1000 * month;
        }
    }