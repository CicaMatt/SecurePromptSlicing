import java.util.*;

public class Solution {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int idx = scanner.nextInt();
        System.out.println(getIdxVal(idx));
    }

    public static String getIdxVal(int index){
        String[] id_sequence= {"a","b","c"};
        if (index < 0 || index >= id_sequence.length) return null;
        else return id_sequence[index];
    }
}