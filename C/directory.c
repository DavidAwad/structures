main() {
   DIR *d;
   struct dirent *e;

   e=malloc(sizeof(struct dirent));
   d=opendir("<your_directory_name>");

   while ((e = readdir(d)) != NULL) {
      printf("%d %s\n", e->d_type, e->d_name);
   }

   closedir(d);
}
