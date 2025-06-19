import java.util.*;
    public class Main {
        public static void main(String[] args) {
            Scanner sc = new Scanner (System.in);
            int n;
            System.out.println("Enter the number");
            n=sc.nextInt();
            
            String [] names = {"Shivam", "Priyansh", "Vibhu", "Yash"};
    
            if(n>0 && n<names.length){
                System.out.println("The value at the index is: " + names[n]);
            } else {
                System.out.println("Invalid index");
            }
        }
    }