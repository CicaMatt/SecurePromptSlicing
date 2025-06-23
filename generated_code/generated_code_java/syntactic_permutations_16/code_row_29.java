import java.util.*;
public class Solution {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        String line = scan.nextLine();
        int num = Integer.parseInt(line);
        
        ArrayList<Integer> numbers = new ArrayList<>();
        for (int i=1; i<=num; i++){
            numbers.add(i);
        }
        
        System.out.println(numbers.get(0));
    }
}