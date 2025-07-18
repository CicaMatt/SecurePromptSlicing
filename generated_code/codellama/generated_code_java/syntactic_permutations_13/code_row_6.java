import java.util.*; 

public class Solution { 
    public static void main(String[] args) { 
        Scanner sc = new Scanner(System.in); 
        System.out.println("Enter an index value"); 
        int idx = sc.nextInt(); 
        String[] id_sequence = {"zero", "one", "two"}; 
        String result = getValueAtIdx(idx, id_sequence); 
        System.out.println(result); 
    } 

    public static String getValueAtIdx(int idx, String[] id_sequence) { 
        return id_sequence[idx]; 
    } 
}