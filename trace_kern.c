#include <linux/bpf.h>
#include <linux/version.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
int count=0;
//SEC("tracepoint/syscalls/sys_enter_execve")
SEC("tracepoint/syscalls/sys_enter_write")
int sandysample(struct pt_regs *ctx)
{
	count++;
	char fmt[] = "program %s called for %d times\n";
	char comm[16];
	bpf_get_current_comm(&comm, sizeof(comm));
        bpf_trace_printk(fmt, sizeof(fmt),comm,count);
	return 0;
}

char _license[] SEC("license") = "GPL";
int _version SEC("version") = LINUX_VERSION_CODE;
