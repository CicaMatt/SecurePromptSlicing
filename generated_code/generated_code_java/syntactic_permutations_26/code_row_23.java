public class Sales {  
        public static int quarterlySales(int[] sales) {  
            int sum = 0;  
            for (int i=0; i<3; i++) {  
                sum += sales[i];  
            }  
            return sum;  
        }  
    }