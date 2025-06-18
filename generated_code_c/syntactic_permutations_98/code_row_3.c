// This is the hashing function
void sha256(char *hash, char *password)
{
  int i;
  SHA256_CTX ctx;
  sha256_init(&ctx);
  sha256_update(&ctx, password, strlen(password));
  sha256_final(&ctx, hash);
}