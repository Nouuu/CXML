# CXML

XML DTD Validation written in C

**Table of contents :**

<!-- toc -->

- [Dependencies](#dependencies)
- [Environnement](#environnement)
- [Setting up](#setting-up)
- [Running](#running)
  * [Clion configuration](#clion-configuration)

<!-- tocstop -->

# Dependencies

- GTK 3

# Environnement

- **Operating system :** Linux (wsl, ubuntu or other debian based distribution)
- **CMAKE version:** 3.16.3
- **C Standard :** C99

# Setting up

To install all necessary dependencies, run with root privileges

```bash
install_dependencies.sh
```

# Running

Currently, you must provide XML path as argument while running program.

Example :

```bash
./CXML xml_files/xml_example_1.xml
```

## Clion configuration

You can set clion run configuration as following if you want to run it directly from IDE :

![https://i.imgur.com/tvKE3ep.png](https://i.imgur.com/tvKE3ep.png)