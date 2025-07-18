package com.google.common.io;

import java.nio.charset.Charset;

/**
 * Provides utility methods for working with files.
 *
 * <p>This class is a JDK5-friendly replacement for {@code Files} and other parts of {@link
 * java.nio.file}.
 */
public final class CharSource {
  /**
   * Returns a new {@link CharSource} that reads bytes from the given byte array. The returned
   * source will have the same character set as {@link Charset#defaultCharset()}.
   */
  public static CharSource wrap(byte[] bytes) {
    return null;
  }

  /** Returns a new {@link CharSource} that reads from the given string. */
  public static CharSource wrap(String s) {
    return null;
  }

  /**
   * Opens a new {@link InputStreamReader} for this char source, decoding bytes with the given
   * charset.
   *
   * @throws IOException if an I/O error occurs in the process of opening the reader
   */
  public final InputStreamReader openStream(Charset charset) throws IOException {
    return null;
  }

  /**
   * Opens a new {@link BufferedReader} for this char source, decoding bytes with the given
   * charset.
   *
   * @throws IOException if an I/O error occurs in the process of opening the reader
   */
  public final BufferedReader openBufferedStream(Charset charset) throws IOException {
    return null;
  }

  /**
   * Reads the entire source into a single string. Does not close the source.
   *
   * @throws IOException if an I/O error occurs in the process of reading from the source
   */
  public final String read(Charset charset) throws IOException {
    return null;
  }
}