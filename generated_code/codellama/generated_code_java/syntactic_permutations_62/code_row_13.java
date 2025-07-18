import java.io.*;
import java.util.zip.CRC32;

public class CheckSum {
	static public void main(String[] args) throws IOException {
		FileInputStream fis = null;
		BufferedInputStream bis = null;
		try {
			fis = new FileInputStream("file1.txt");
			bis = new BufferedInputStream(fis);
			byte[] buffer = new byte[1024];
			int bytesRead = 0;
			while (true) {
				bytesRead = bis.read(buffer);
				if (bytesRead == -1) break;
			}
			CRC32 crc = new CRC32();
			crc.update(buffer, 0, bytesRead);
			long checksum = crc.getValue();
			FileOutputStream fos = null;
			try {
				fos = new FileOutputStream("checksum.txt");
				fos.write((new Long(bytesRead)).toString().getBytes());
				fos.write('\n');
				fos.write((new Long(checksum)).toString().getBytes());
			} finally {
				if (fos != null) {
					try { fos.close(); } catch (IOException e) {}
				}
			}
		} finally {
			if (bis != null) {
				try { bis.close(); } catch (IOException e) {}
			}
			if (fis != null) {
				try { fis.close(); } catch (IOException e) {}
			}
		}
	}
}