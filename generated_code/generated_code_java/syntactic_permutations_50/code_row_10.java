import java.io.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
public class Unzipper {
	public static void main(String[] args) throws IOException {
		byte[] buffer = new byte[1024];
		ZipInputStream zis = new ZipInputStream(new FileInputStream("archive.zip"));
		try {
			ZipEntry ze;
			while ((ze = zis.getNextEntry()) != null) {
				String fileName = ze.getName();
				File newFile = new File("/tmp/unpack/" + fileName);
				new File(newFile.getParent()).mkdirs();
				FileOutputStream fos = new FileOutputStream(newFile);
				try {
					int len;
					while ((len = zis.read(buffer)) > 0) {
						fos.write(buffer, 0, len);
					}
				} finally {
					fos.close();
				}
			}
		} finally {
			zis.closeEntry();
			zis.close();
		}
	}
}