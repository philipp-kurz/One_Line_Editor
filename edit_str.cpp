#include "edit_str.h"

int edit_str(char* ld_str, char* ed_str, char* tr_str, int ed_length) {

	static int pos = 0;
	struct pos initPos;
	unsigned char ascii, scan;

	static int insert = 0; /* 0 => overwrite, 1 => insert */
	setcursortype(99);

	for (int i = 0; i < (int)strlen(ld_str); i++) putchar(ld_str[i]);

	initPos.x = wherex();
	initPos.y = wherey();

	for (int i = 0; i < ed_length; i++) putchar(ed_str[i]);
	for (int i = 0; i < (int)strlen(tr_str); i++) putchar(tr_str[i]);

	gotoxy(initPos.x, initPos.y);

	int last_digit = ed_length - 1;
	pos = 0;

	do {
		scan = 0;
		ascii = _getch();

		if (ascii == 0x00 || ascii == 0xE0 || ascii == 0x08)
		{
			if (ascii == 0x00 || ascii == 0xE0) {
				ascii = 0;
				scan = _getch();
			}
			else {
				scan = ascii;
				ascii = 0;
			}

			switch (scan) {

			case 8: /* Backspace Key */
				if (wherex() > initPos.x) {
					gotoxy(wherex() - 1, wherey());

					for (int i = pos - 1; i < last_digit; i++) {
						ed_str[i] = ed_str[i + 1];
						putchar(ed_str[i]);
					}

					ed_str[last_digit] = ' ';
					putchar(' ');
					pos--;
					gotoxy(initPos.x + pos, initPos.y);
				}
				else putchar('\a');
				break;

			case 83: /* Delete Key */
				if (ed_str[pos] != 0) {
					for (int i = pos; i < last_digit; i++) {
						ed_str[i] = ed_str[i + 1];
						putchar(ed_str[i]);
					}
					ed_str[last_digit] = ' ';
					putchar(' ');
					gotoxy(initPos.x + pos, initPos.y);
				}
				else putchar('\a');
				break;

			case 75: /* Left Arrow Key */
				if (wherex() > initPos.x) {
					gotoxy(wherex() - 1, wherey());
					pos--;
				}
				else putchar('\a');
				break;

			case 77: /* Right Arrow Key */
				if ((wherex() < initPos.x + ed_length - 1) && ed_str[pos + 1] != 0) {
					gotoxy(wherex() + 1, wherey());
					pos++;
				}
				else putchar('\a');
				break;

			case 71: /* Pos1 Key */
				gotoxy(initPos.x, initPos.y);
				pos = 0;
				break;

			case 79: /* End Key */
				pos = 0;
				while (ed_str[pos] != 0) pos++;
				gotoxy(initPos.x + pos, initPos.y);
				break;

			case 82: /* Insert Key */
				if (insert == 0) {
					insert = 1;
					setcursortype(10);
				}
				else {
					insert = 0;
					setcursortype(99);
				}
				break;
			default: break;
			}
		}

		if (ascii > 31) {

			if (pos <= last_digit) {

				if (insert == 0) {
					ed_str[pos] = ascii;
					putchar(ascii);
					pos++;
					if (pos > last_digit) {
						gotoxy(initPos.x + ed_length - 1, initPos.y);
						pos = ed_length - 1;
					}
				}
				else {
					int index = 0;

					do {
						ed_str[last_digit - index] = ed_str[last_digit - index - 1];
						index++;
					} while ((pos + index + 1) <= ed_length);

					putchar(ascii);
					ed_str[pos] = ascii;
					for (int i = pos + 1; i <= last_digit; i++) putchar(ed_str[i]);
					gotoxy(initPos.x + pos + 1, initPos.y);
					pos++;
				}
			}
		}

	} while (ascii != 13);


	int length = 0;
	while (ed_str[length] != 0) length++;
	return length;
}

