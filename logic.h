void edit_str(char *input) {
    for (int i = 0; input[i]; i++) {
        char c = input[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') {
            input[i] += 'A' - 'a';
        }
    }
}