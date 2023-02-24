src = $(wildcard src/*.c)
obj = $(src:.c=.o)
dep = $(obj:.o=.d)

NAME = ACPIWMI.dll

LDFLAGS = -Iinclude -shared -Wl,--enable-stdcall-fixup
CFLAGS = -m32 -MMD
-include $(dep)

$(NAME): $(obj)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ acpiwmi.def

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -f $(obj) $(dep) $(NAME)