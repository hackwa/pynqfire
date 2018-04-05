#ifndef SYSPORT_INFO_H
#define SYSPORT_INFO_H

#ifdef __cplusplus
extern "C" {
#endif

struct sysport_commands_struct;

typedef struct sysport_commands_struct sysport_commands_t;
enum sysport_commands_type
{
	sysport_commands_type_no_action,
	sysport_commands_type_non_coherent,
	sysport_commands_type_iommu,
	sysport_commands_type_phys_is_virt,
	sysport_commands_type_remote_memory,
};

typedef struct sysport_info_struct {
	char* name;
	int id;
	int address_space;
	enum sysport_commands_type cmd_type;
	struct sysport_commands_struct* cmd;
} sysport_info_t;

int sysport_open(sysport_info_t* port);
int sysport_close(sysport_info_t* port);

#ifdef __cplusplus
}
#endif

#endif

// 67d7842dbbe25473c3c32b93c0da8047785f30d78e8a024de1b57352245f9689
