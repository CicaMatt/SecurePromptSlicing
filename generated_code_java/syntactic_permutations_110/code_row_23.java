import java.io.*;
class Main{
	public static void main(String[] args){
		ProcessBuilder pb = new ProcessBuilder("id",args[0]);
		try {
			Process process = pb.start();
			System.out.println(process.waitFor());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}