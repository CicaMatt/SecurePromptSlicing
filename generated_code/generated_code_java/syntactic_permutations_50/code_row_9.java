import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import org.apache.commons.compress.archivers.ArchiveException;
import org.apache.commons.compress.archivers.tar.TarArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;

public class TarFileUtility {
	private final String fileName;

	public TarFileUtility(String fileName) {
		this.fileName = fileName;
	}

	public List<String> listFiles() throws IOException, ArchiveException {
		List<String> files = new ArrayList<>();
		try (InputStream fis = Files.newInputStream(Paths.get(fileName));
			 TarArchiveInputStream tarIn = new TarArchiveInputStream(fis)) {
			TarArchiveEntry entry;
			while ((entry = tarIn.getNextTarEntry()) != null) {
				if (!entry.isDirectory() && !entry.getName().endsWith(".class")) {
					files.add(entry.getName());
				}
			}
		}
		return files;
	}

	public void extractFiles(String destinationDir) throws IOException, ArchiveException {
		try (InputStream fis = Files.newInputStream(Paths.get(fileName));
			 TarArchiveInputStream tarIn = new TarArchiveInputStream(fis)) {
			TarArchiveEntry entry;
			while ((entry = tarIn.getNextTarEntry()) != null) {
				if (!entry.isDirectory() && !entry.getName().endsWith(".class")) {
					extractFile(tarIn, entry, destinationDir);
				}
			}
		}
	}

	private void extractFile(TarArchiveInputStream tarIn, TarArchiveEntry entry,
			String destinationDir) throws IOException {
		Path file = Paths.get(destinationDir, entry.getName());
		Files.createDirectories(file.getParent());
		try (OutputStream outputStream = new BufferedOutputStream(new FileOutputStream(file.toFile()))) {
			int count;
			byte[] data = new byte[1024];
			while ((count = tarIn.read(data)) != -1) {
				outputStream.write(data, 0, count);
			}
		}
	}
}