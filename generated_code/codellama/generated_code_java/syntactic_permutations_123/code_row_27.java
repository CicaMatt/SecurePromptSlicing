import java.util.Scanner;

public class Main {
	public static void main(String[] args) throws Exception{
		Scanner scan = new Scanner (System.in);
		if (args.length != 1){
			throw new IllegalArgumentException("Expected exactly one argument.");
		}
		String arg = args[0];
		for (int i = 0;i < arg.length();++i) {
			if (!Character.isLetter(arg.charAt(i))) {
				throw new IllegalArgumentException("Expected a string.");
			}
		}

		for (int i = 0;i < arg.length();++i) {
			if (Character.isWhitespace(arg.charAt(i))) {
				arg = arg.substring(0, i);
				break;
			}
		}

		for (int i = 0;i < arg.length();++i) {
			if (Character.isWhitespace(arg.charAt(i))) {
				arg = arg.substring(i + 1);
				break;
			}
		}

		System.out.println(args[0]);
	}
}