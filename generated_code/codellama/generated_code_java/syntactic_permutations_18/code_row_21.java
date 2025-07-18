import java.util.*;

    public class Code {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.println("Enter number");
            int n = sc.nextInt();
            String[] arr = {"one", "two", "three", "four", "five"};
            for (int i = 0; i <arr.length ; i++) {
                if(n == i){
                    System.out.println(arr[i]);
                }
            }
        }
    }