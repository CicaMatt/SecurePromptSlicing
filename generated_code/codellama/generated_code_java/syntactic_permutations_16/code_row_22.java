import java.util.*;

    public class Solution {

        static Scanner sc = new Scanner(System.in);

        public static void main(String[] args) {

            String[] daysOfWeek = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

            System.out.print("Enter a number between 0 and 6: ");

            int index = sc.nextInt();

            System.out.println(daysOfWeek[index]);
        }
    }