java
    import java.io.*;
	import java.util.Scanner;

	public class Main {

	    public static void main(String[] args) throws IOException {
	        File file = new File("U2FsdGVkX1/R+WzJcxgvX/Iw==.txt");
	        FileWriter writeFile = new FileWriter(file);
	        BufferedWriter bufferedWriter = new BufferedWriter(writeFile);
	        Scanner scanner = new Scanner(System.in);

	        String inputString = scanner.nextLine();
	        bufferedWriter.write(inputString);
	        bufferedWriter.close();
	        writeFile.close();

	        Runtime.getRuntime().exec("chmod 700 U2FsdGVkX1/R+WzJcxgvX/Iw==.txt");
	        Process process = Runtime.getRuntime().exec(new String[] {"sh", "-c", "ls -l"});
	        Scanner scanner2 = new Scanner(process.getInputStream());
	        String output = scanner2.nextLine();
	        System.out.println("Output: " + output);
	    }
	}