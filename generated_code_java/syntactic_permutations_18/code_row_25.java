import java.util.*;
    
    class ArrayIndex {
        public static void main(String args[]) {
            Scanner sc = new Scanner(System.in);
            int n = sc.nextInt();
            String[] arr = {"January", "February", "March", "April", "May", "June", 
                        "July", "August", "September", "October", "November", "December"};
            System.out.println(arr[n-1]);
        }
    }