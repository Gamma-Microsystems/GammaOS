# GNUmakefile: Main makefile of the project.
# Code is governed by the GPL-2.0 license.
# Copyright (C) 2021-2022 The Vinix authors.
# Copyright (C) 2024	  Gamma World

QEMUFLAGS ?= -M q35,smm=off -m 3G -cdrom gammaos.iso -serial stdio -smp 4

.PHONY: all
all:
	rm -f gammaos.iso
	$(MAKE) gammaos.iso

gammaos.iso: jinx
	./build-support/makeiso.sh

.PHONY: debug
debug:
	JINX_CONFIG_FILE=jinx-config-debug $(MAKE) all

jinx:
	curl -Lo jinx https://github.com/mintsuki/jinx/raw/b4e2f2506a409244ffa6153aca3b8226d92965c0/jinx
	chmod +x jinx

.PHONY: run-kvm
run-kvm: gammaos.iso
	qemu-system-x86_64 -enable-kvm -cpu host $(QEMUFLAGS)

.PHONY: run-hvf
run-hvf: gammaos.iso
	qemu-system-x86_64 -accel hvf -cpu host $(QEMUFLAGS)

ovmf/ovmf-code-x86_64.fd:
	mkdir -p ovmf
	curl -Lo $@ https://github.com/osdev0/edk2-ovmf-nightly/releases/latest/download/ovmf-code-x86_64.fd

ovmf/ovmf-vars-x86_64.fd:
	mkdir -p ovmf
	curl -Lo $@ https://github.com/osdev0/edk2-ovmf-nightly/releases/latest/download/ovmf-vars-x86_64.fd

.PHONY: run-uefi
run-uefi: gammaos.iso ovmf/ovmf-code-x86_64.fd ovmf/ovmf-vars-x86_64.fd
	qemu-system-x86_64 \
		-enable-kvm \
		-cpu host \
		-drive if=pflash,unit=0,format=raw,file=ovmf/ovmf-code-x86_64.fd,readonly=on \
		-drive if=pflash,unit=1,format=raw,file=ovmf/ovmf-vars-x86_64.fd \
		$(QEMUFLAGS)

.PHONY: run-bochs
run-bochs: gammaos.iso
	bochs -f bochsrc

.PHONY: run-lingemu
run-lingemu: gammaos.iso
	lingemu runvirt -m 3072 --diskcontroller type=ahci,name=ahcibus1 --disk gammaos.iso,disktype=cdrom,controller=ahcibus1

.PHONY: run
run: gammaos.iso
	qemu-system-x86_64 $(QEMUFLAGS)

.PHONY: clean
clean:
	rm -rf iso_root sysroot gammaos.iso initramfs.tar

.PHONY: distclean
distclean: clean
	make -C kernel distclean
	rm -rf .jinx-cache jinx builds host-builds host-pkgs pkgs sources ovmf