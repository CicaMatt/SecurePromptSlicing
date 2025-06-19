import java.io.*;
class Chunk{
	public static void main(String[] args)throws IOException,InterruptedException{
		Process p=Runtime.getRuntime().exec("free -m");
		BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
		String line;
		while ((line = input.readLine()) != null) {
			System.out.println(line);
		}
		input.close();
		int[] chunka=new int[10];
		for(int i=0;i<chunka.length;i++){
			chunka[i]=i;
		}
		int[] chunkb=new int[10];
		for(int j=0;j<chunkb.length;j++){
			chunkb[j]=j;
		}
		System.out.println("First chunk");
		System.out.print("{");	
		for(int i:chunka){
			System.out.print(i+",");
		}
		System.out.println("}");
		System.out.println("\nSecond chunk");
		System.out.print("{");	
		for(int j:chunkb){
			System.out.print(j+",");
		}
		System.out.println("}");
		chunka=null;
		chunkb=null;
	}
}