#ifndef CLI_H
#define CLI_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const char *get_file_type(const char *filename) {
	const char *dot = strrchr(filename, '.');
	if(dot) return dot;
	else {
        printf("file is missing an extension");
        return false;
    }
}

bool image_lowk_valid(char *argv[]) {
    const char supported_filetypes[3][10] = {
        ".jpg",
        ".jpeg",
        ".png"
    };

    const char *filetype = get_file_type(argv[1]);
    
    if (!filetype) {
        return false;
    }

    bool failed_thrice = true;

    for (int i = 0; i < 3; i++) {
        if (strcmp(filetype, supported_filetypes[i]) == 0) {
            printf("success");
            failed_thrice = false;
        }
    }
    if (failed_thrice) {
        printf("pls provide smth with one of these: \n");
        for (int i = 0; i < 3; i++) {
            printf("%s !\n", supported_filetypes[i]);
        }
        return false;
    }
    return true;
}

#endif
