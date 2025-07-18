import java.util.*;
import java.io.*;
import tarfile;
import gzip;
public class Unpack {
	public static void main(String[] args) throws IOException{
		String filename = "archive.tar.gz";
		File file = new File(filename);
		if (!file.exists() || !file.canRead()) {
			System.out.println("Cannot read file");
			return;
		}
		BufferedOutputStream dest = null;
		FileInputStream fis = new FileInputStream(file);
		GzipCompressorInputStream gzIn = new GzipCompressorInputStream(fis);
		try {
			TarArchiveInputStream tarIn = new TarArchiveInputStream(gzIn);
			TarArchiveEntry entry = null;
			while ((entry = tarIn.getNextTarEntry()) != null) {
				if (entry.isDirectory()) {
					continue;
				}
				int count;
				byte data[] = new byte[BUFFER];
				FileOutputStream fos = new FileOutputStream(entry.getName());
				dest = new BufferedOutputStream(fos, BUFFER);
				while ((count = tarIn.read(data, 0, BUFFER)) != -1) {
					dest.write(data, 0, count);
				}
				dest.flush();
				dest.close();
			}
			tarIn.close();
		} catch (Exception e) {
			System.out.println("Error found: " + e);
			return;
		} finally {
			if (gzIn != null) {
				gzIn.close();
			}
			if (fis != null) {
				fis.close();
			}
		}
	}
	private static final int BUFFER = 2048;
}