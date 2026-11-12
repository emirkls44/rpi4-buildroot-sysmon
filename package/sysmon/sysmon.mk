SYSMON_VERSION = 1.0
SYSMON_SITE = $(BR2_EXTERNAL_SYSMON_PATH)/src/sysmon
SYSMON_SITE_METHOD = local
SYSMON_LICENSE = MIT

define SYSMON_BUILD_CMDS
	$(TARGET_CC) $(TARGET_CFLAGS) $(TARGET_LDFLAGS) -Wall -Wextra \
		-o $(@D)/sysmon $(@D)/sysmon.c
endef

define SYSMON_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/sysmon $(TARGET_DIR)/usr/bin/sysmon
endef

define SYSMON_INSTALL_INIT_SYSV
	$(INSTALL) -D -m 0755 $(SYSMON_PKGDIR)/S99sysmon $(TARGET_DIR)/etc/init.d/S99sysmon
endef

$(eval $(generic-package))
