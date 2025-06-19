import java.io.*;
import java.util.zip.CRC32;

public class Solution {
	public static void main(String[] args) throws Exception{
		FileReader fr = new FileReader("file1");
        BufferedReader br = new BufferedReader(fr);
        StringBuffer sb = new StringBuffer();
        String line;
        while((line=br.readLine())!=null){
            sb.append(line+"\n");
        }
        byte[] buf = sb.toString().getBytes();
        CRC32 crc = new CRC32();
        crc.update(buf);
        FileWriter fw = new FileWriter("file2");
        BufferedWriter bw = new BufferedWriter(fw);
        bw.write(Integer.toString(buf.length)+"\n");
        bw.write(Long.toString(crc.getValue()));
        bw.close();
	}
}