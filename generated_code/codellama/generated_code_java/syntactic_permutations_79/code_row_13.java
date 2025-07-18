import java.util.Scanner;
    
    public class Solution {
    	public static void main(String[] args) {
    
    		int buf = 1024;
    		int buf1 = 1024;
    
    		byte[] array = new byte[buf];
    		byte[] array1 = new byte[buf1];
    
    		System.out.println("Enter the characters");
    		Scanner scanner = new Scanner(System.in);
    		String s = scanner.nextLine();
    		for (int i = 0; i < s.length(); i++) {
    			array[i] = (byte) s.charAt(i);
    		}
    		System.out.println("Enter the characters");
    		String s1 = scanner.nextLine();
    		for (int i = 0; i < s1.length(); i++) {
    			array1[i] = (byte) s1.charAt(i);
    		}
    	}
    }