import java.util.*;
class Program {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String s = sc.nextLine();
		if (s instanceof String) {
			for (int i = 0; i < s.length(); i++) {
				if (Character.isWhitespace(s.charAt(i))) {
					s = s.substring(0, i);
					break;
				}
			}
			for (int i = 0; i < s.length(); i++) {
				if (s.charAt(i) == '\n') {
					s = s.substring(0, i);
					break;
				}
			}
			System.out.println(s + "\0");
		}
	}
}