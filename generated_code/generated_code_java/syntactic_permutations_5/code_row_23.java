import java.util.*;
public class Solution{
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        List<Integer> list = new ArrayList<>();
        for (int i = 1; i <= 9; i++) {
            list.add(n*i);
        }
        System.out.println(list.get(list.size()-1));
    }
}