#include <stdio.h>
#include <unistd.h>
#include <bpf/libbpf.h>

int main(int ac, char **argv)
{
	struct bpf_link *link = NULL;
	struct bpf_program *prog;
	struct bpf_object *obj;

	obj = bpf_object__open_file("trace_kern.o", NULL);
	if (libbpf_get_error(obj)) {
		fprintf(stderr, "ERROR: opening BPF object file failed\n");
		return 0;
	}else{
		printf("sandy: You got the ebpf program\n");
	}

	prog = bpf_object__find_program_by_name(obj, "sandysample");
	if (!prog) {
		fprintf(stderr, "ERROR: finding a prog in obj file failed\n");
		goto cleanup;
	}else{
		printf("You got the program function now\n");
	}

	/* load BPF program */
	if (bpf_object__load(obj)) {
		fprintf(stderr, "ERROR: loading BPF object file failed\n");
		goto cleanup;
	}else{
		printf("You loaded the object now\n");
	}

	link = bpf_program__attach(prog);
	if (libbpf_get_error(link)) {
		fprintf(stderr, "ERROR: bpf_program__attach failed\n");
		link = NULL;
		goto cleanup;
	}

	while(true){
	}
cleanup:
	bpf_link__destroy(link);
	bpf_object__close(obj);
	return 0;
}
